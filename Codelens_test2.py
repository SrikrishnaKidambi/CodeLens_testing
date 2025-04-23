def merge_sort(arr):
    # Base case: if array has one or zero elements, it's already sorted
    if len(arr) > 1:
        # Find the middle point to divide the array
        mid = len(arr) // 2
        # Split the array into two halves
        left_half = arr[:mid]
        right_half = arr[mid:]

        # Recursively sort the two halves
        merge_sort(left_half)
        merge_sort(right_half)

        # Initialize indices for merging
        i = j = k = 0

        # Merge the two sorted halves back into arr
        while i < len(left_half) and j < len(right_half):
            if left_half[i] < right_half[j]:
                arr[k] = left_half[i]
                i += 1
            else:
                arr[k] = right_half[j]
                j += 1
            k += 1

        # Copy any remaining elements from the left half
        while i < len(left_half):
            arr[k] = left_half[i]
            i += 1
            k += 1

        # Copy any remaining elements from the right half
        while j < len(right_half):
            arr[k] = right_half[j]
            j += 1
            k += 1

if __name__ == "__main__":
    my_list = [38, 27, 43, 3, 9, 82, 10]
    print("Original array:", my_list)
    # Call merge sort to sort the list
    merge_sort(my_list)
    print("Sorted array:", my_list)